var cryptoLuck;
var userAccount;

async function startApp()
{
    var cryptoLuckAddress = "0x34ab497764b6e6f11a60f9a20dc678b2b3d9a7e3";
    cryptoLuck = web3js.eth.contract(abi).at(cryptoLuckAddress);

    var accountInterval = setInterval(function() {
        if (web3.eth.accounts[0] !== userAccount) userAccount = web3.eth.accounts[0];
    }, 100);
}
      
async function gamble(name,id,vote)
{
    $("#txStatus").text("Submitting your vote.This may take a while...");

    let result = await promisify(cb => cryptoLuck.gamble(name,id,vote,cb));
    let hash = await promisify(cb => web3.eth.getTransactionReceipt(result,cb));
    while(hash == null) hash = await promisify(cb => web3.eth.getTransactionReceipt(result,cb));
    if (hash.status !== "0x0")
    {
        console.log(hash);
        $("#txStatus").text("Vote submitted succesfully");
    }
    else $("#txStatus").text("Transaction failed,please try again");
}

async function setTime()
{
    let x = await promisify(cb => cryptoLuck.getTime(cb));
    x = 86400 - (Math.floor(x) + 3600) % 86400;
    app.time =  [Math.floor(x / 3600),Math.floor((x % 3600) / 60),(x % 3600) % 60];
    app.startInterval();
}
      
window.addEventListener('load', function()
{

    if (typeof web3 !== 'undefined')
    {
        web3js = new Web3(web3.currentProvider);
        ethereum.enable();
        
    }
    else web3js = new Web3();
    startApp();
})

const promisify = (inner) =>
    new Promise((resolve, reject) =>
        inner((err, res) => {
            if (err) {
                reject(err);
            } else {
                resolve(res);
            }
        })
    );

window.onload = function() {
    setTime();
}