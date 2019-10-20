from flask import Flask,render_template
from scraper import scrape,get_pic,load_pic,loaded
app=Flask(__name__)

@app.route('/')
def index():
    if not loaded():
        return 'no picture! please load!'
    src = get_pic()
    print(src)
    return render_template('index.html',src=src)
@app.cli.command()
def load():
    load_pic()
if __name__ == "__main__":
    app.run(debug=True)