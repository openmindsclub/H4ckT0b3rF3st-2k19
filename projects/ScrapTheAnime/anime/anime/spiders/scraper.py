import scrapy

try:
    with open("animes.csv","r") as f:
        pass
except:
    with open("animes.csv","w") as f:
        f.write("Anime,Studio,Source,Episodes,Link\n")

class AnimeSpider(scrapy.Spider):
    name = "anime"

    def start_requests(self):
        urls = [
            "https://myanimelist.net/anime/season"
        ]
        for url in urls:
            yield scrapy.Request(url=url, callback=self.parse)

    def parse(self, response):
        #to fill

