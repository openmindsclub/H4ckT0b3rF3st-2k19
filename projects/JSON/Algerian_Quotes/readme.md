# A collection of Arabic proverbs:
This project aim to create a collection of Algerian proverbs / quotes from your favorite *`writer`*, *`poets`* , *`singer`* or your *`grandmother`*! and help beginners to get into contribution.
## How to contribute:
**Add JSON object of the form:**
```
{
    "quote":"",
    "language":"",
    "translation":"",
    "region":"",
    "meaning":"",
    "author":""
}
```
> **`quotes`**   :proverb written in Latin or Arabic

> **`language`** : the language with which the proverb / quote is written, the accepted values ​​are:
+ `"French"` : if the proverb / quote is written in French
+ `"Arabic"` : if the proverb / quote is written in Arabic
+ `"Amazigh"` : if the proverb / quote is written in Latin-Amazigh

>**`translation`**:the translation of the proverb in *`English`*.

> **`region`**   : **[Not necessary]** the native region of the proverb / quote if any

> **`meaning`**  : **[Not necessary]** the meaning of the proverb / quote

> **`author`**  : **[Not necessary]** the author if known

**in the array of the file `Arabic_Quotes.json`**
### **Example:**
```
[
    {
    "quote":"ما لم يكن مقدرا لك لن يأتيك و لو كان بين شفتيك",
    "language":"Arabic",
    "translation":"what you are not destined for will never be yours, even if you have it between your lips",
    "region":"",
    "meaning":"what you are not destined for will never be yours no matter what you do",
    "author":""
    },
    {
    "quote":"Lmenghi gizmawen yiwen was win kdjan koulas",
    "language":"Amazigh",
    "translation":"The quarrels between lions last only one day, the one between dogs last many days",
    "region":"Kabylie",
    "meaning":"Valiants do not seek conflict",
    "author":""
    }
]
```
 P.S :  json elements are separated by a comma.
