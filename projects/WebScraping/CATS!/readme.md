# CAT PICTURE SCRAPER :
### who doesn't like cats, right ? ,here we wan't to create a web site full of cat pictures and the best one are in [`/r/cats`](https://old.reddit.com/r/cats/ "Cats Subreddit.")

## **DONE** :
+ Flask web app
+ scraper boilerplate
+ html & css files
### **INFO:**
 okay so we have the web site , now we need to fill it with CATS!!,
+ *we want to get the url of cat images there's is in [`/r/cats`](https://old.reddit.com/r/cats/ "Cats Subreddit.")*
+ *we want to get only the first page pictures*


  ## **TO DO:**
 + there's some methods you need to fill in scraper.py
 + *`scrape():`* this method must return an array of all cat images url there's in the first page
 + *`load_pic():`* this method load an array object into the `url_list` file
 + *`get_pic():`* this method load an array object into the `url_list` file
 + *`loaded():`* this method check if the `url_list` has element in it or not

p.s: you can add methods or files if you want to,

### **Setup:**
```
$ sudo apt install python3-pip
```
```
$ pip install Flask
```
```
$ pip install requests
```
```
$ pip install beautifulsoup4
```
+ **To init:**
```
$ python3 app.py
``` 
+ *output:*
```
 * Serving Flask app "app" (lazy loading)
 * Environment: production
   WARNING: This is a development server. Do not use it in a production deployment.
   Use a production WSGI server instead.
 * Debug mode: on
 * Running on http://127.0.0.1:5000/ (Press CTRL+C to quit)
 * Restarting with stat
 * Debugger is active!
 * Debugger PIN: 239-737-751
```
+ **To load the url array in the file** 
```
$ Flask load
```
### **Documentation:**
+ [Web Scraping 101 with Python & Beautiful Soup](https://codeburst.io/web-scraping-101-with-python-beautiful-soup-bb617be1f486 "codeburst")
+ [Scraping Reddit](https://www.datacamp.com/community/tutorials/scraping-reddit-python-scrapy "DataCamp")
