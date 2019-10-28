## Scrap The Anime
This is a python project to scrape seasonal animes from [MyAnimeList](https://myanimelist.net) using [Scrapy](https://scrapy.org).

### Setup
You need to install Scrapy:
``` bash
pip install Scrapy
```

### Usage
To scrap the seasonal animes,go through these steps:
``` bash
$ cd animes
$ scrapy crawl anime
[outputs logs]
$ cat animes.csv
[outputs the animes and their info]
```

### Tasks
Here are things you can do to complete this implementation:
* Complete the `parse` method to parse the following info: 
    * Anime name
    * Anime studio
    * Anime source
    * Anime number of episodes
    * Anime link in myanimelist
* Export the info in a MarkDown file(better view)
* Make the script crawl multiple seasons of a certain year(summer,fall,winter,spring)
* Be creative!

### Ressources
* [Scrapy Tutorial](https://docs.scrapy.org/en/latest/intro/tutorial.html)

#### Happy Hacking!