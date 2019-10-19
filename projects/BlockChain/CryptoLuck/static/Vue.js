Vue.component(VueCarousel.name, VueCarousel);

const app = new Vue({
    el: "#app",
    data: {
        images: [
            "<figure class='image container'><img src='static/img/fsf.svg' /></figure>",
            "<figure class='image container'><img src='static/img/gnu.svg' /></figure>",
            "<figure class='image container'><img src='static/img/gplv3.svg' /></figure>"
        ],
        fields: {
            "nom": "text",
            "prenom": "text",
            "matricule": "number",
            "vote": "number"
        },
        nom: "",
        prenom: "",
        matricule: "",
        vote: 0,
        time: [24,0,0],
        timer: null,
        currentIndex: 0
    },
    methods: {
        startSlide: function() {
            this.timer = setInterval(this.next, 4000);
        },
      
        next: function() {
            this.currentIndex += 1;
        },
        prev: function() {
            this.currentIndex -= 1;
        },
        updateTime: function(o) {
            if (this.time[o] == 0 && o) {
                this.time.splice(o,1,59);
                this.updateTime(o-1);
            }
            else this.time.splice(o,1,this.time[o]-1);
        },

        startInterval: function () {
            setInterval(() => this.updateTime(2), 1000);
        },
        submitForm: async function() {
            let name = this.nom + " " + this.prenom;
            await gamble(name,this.matricule,this.vote);
        }

          
    },
    computed: {
        currentImg: function() {
            return this.images[Math.abs(this.currentIndex) % this.images.length];
          },
        currentTime: function() {return setInterval(this.updateTime(2),1000);}
    }
    
});