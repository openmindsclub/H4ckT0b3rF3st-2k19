#!/usr/bin/ruby
#implication
class TrueClass
    def >> q
	 q;
    end
end
class FalseClass
    def >> q
	true;
    end
end
module Operations
	def ^ y
		y.is_a?(Numeric) ? super : (self==1) ^ y;
	end
	def & y
		y.is_a?(Numeric) ? super : (self == 1) & y;
	end
    def | y
		y.is_a?(Numeric) ? super : (self == 1) | y;
    end
end
#Avoid Fixnum^boolean
class Integer
	prepend Operations;
	def gray
		self ^ (self >> 1);
	end
end
begin
require'io/console';
puts 'Fait par Akram Bourouina'
puts 'Entrez la fonction logique (variables a,b,c,d...)';
signes = { '+' => '||','.'=>'&&'};
BINARY = [ ];
inp = gets.downcase;
inp.gsub!(/[a-z](?=[!a-z\(])/){|c| c + ?.};
inp.gsub!(/(?<=\))[a-z!]/){|c| ?. + c};
inp.gsub!(/(?<!<)=>/, '>>');
expr = inp.gsub(/[+\.]/, signes);
n = expr.scan(/[a-z]/).sort.last.ord - 96;
names = (?a .. ?z).first(n);
rows = [ "\n#{?-*76}\nFONCTION LOGIQUE : \n", "F = #{inp}\n#{?-*76}\n", "TABLE DE VERITE : \n"];
rows << " #{names.join(' | ')} | F ";
rows << ('-'*(4*n+3));
f = -> t {
    t = t.map{|x| x == 1};
    eval(expr.gsub(/[a-z]/){|c| "t[#{c.ord-97}]"}) ? 1 : 0;
}
 results = [ ];
(2**n).times{|i|
    bin = i.to_s(2);
    BINARY[i] = bin;
    s = bin.rjust(n,?0);
    args = s.chars.map(&:to_i);
    res = f.(args);
    results << res;
    rows << " #{args.join(' | ')} | #{res} ";
};
#MAKE KARNAUGH
karnaugh_rows = [ ];
max_left = n / 2;
max_top = n - max_left;
lefts = [ ];
tops = [ ];
(2**max_left).times{|left|
	grayleft = left.gray;
	bin_grayleft = BINARY[grayleft];
	lefts << bin_grayleft.rjust(max_left, ?0);
	_row = [ ];
	(2**max_top).times{|top|
		grayleft, graytop = left.gray, top.gray;
		bin_graytop = BINARY[graytop].rjust(max_top,?0);
		tops << bin_graytop;
		num = (bin_grayleft + bin_graytop).to_i(2);
		_row << results[num];
	}
	karnaugh_rows << _row;
}
karnaugh_str = [ " #{names.first(max_left).join}/#{names.last(max_top).join} | #{(2**max_top).times.map{|i| BINARY[i.gray].rjust(max_top,?0)}.join(' | ')} "];
lefts.each_with_index{|c,i|
	karnaugh_str << " #{c}#{' '*(1+max_top)} | #{karnaugh_rows[i].map{|c| c.to_s.rjust(max_top,' ')}.join(' | ')} ";
}
#MAKE KARNAUGH
rows << "\n#{?-*76}\nTABLE DE KARNAUGH : \n";
rows.concat(karnaugh_str);
rows << "\n#{?-*76}\n";
txt = rows.join(?\n);
puts txt;
puts 'Voulez vous enregistrer la sortie dans un fichier? O/N';
inp = IO.console.getch.upcase until inp == ?N || inp == ?O;
exit 0 if inp == ?N;
new_index = Dir.entries(?.).map{|v| v[/^TV (\d+)\.txt$/, 1].to_i}.max + 1;
$filename = "TV #{new_index}.txt";
File.open($filename, ?w) do|f|
    f.write(txt);
end;
puts "\nFini, le fichier #{$filename} vient d'etre cree";
rescue StandardError => e
    p e.message;
    p e.backtrace;
ensure
    print ?\n;
    puts 'Appuyez sur une touche pour fermer';
    gets;
end
