# markTxn

See https://github.com/chuck-h/markTxn/blob/main/markTxn/ricardian/markTxn.clauses.md

A typical contract call:
```
{
  "actions":[
    {
      "account":"marksaccount",
      "name":"mark",
      "authorization":[
        {
          "actor":"...........1",
          "permission":"...........2"
        }
      ],
      "data":{
        "txn":"1c1a9564ba1d24bd2859663c6d5b7942d461358ecaba5c746065096659fdbc5e
",
        "category":"services",
        "confidence":"100",
        "fraction":"100",
        "memo":"haircut"
      }
    }
  ]
}
```

For testing an eosio signing request and QR code can be generated with web tools like
* https://github.com/greymass/eosio-uri-builder
* https://www.qrcode-monkey.com/

    
