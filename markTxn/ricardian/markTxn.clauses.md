<h1 class="clause">Purpose</h1>

This contract supports a lightweight system for annotating payments made on chain. This is intended to support analysis of how the economic system is working.

The contract itself implements no semantics, although default semantics are described in the ricardian contract. There is no validation or protection against erroneous annotations, whether by mistake or malice. Persons writing analysis tools would be advised to implement outlier checking and filtering (e.g. based on a whitelist of annotators).
1. mark - assigns a category (e.g. "product sale") to a transaction
2. register - adds a new category name to the list of acceptable categories
3. unregister - removes a category name

<h1 class="clause">Issuing Actions</h1>

Example
```
cleos -u https://api.telos.caleos.io push transaction '{
...
```

<h1 class="clause">Effect</h1>

This contract leaves only a "journal" of labeling events on the blockchain. The contract contains no database which can be queried about annotations. (The only table maintained by the contract is a list of known category names.)

<h1 class="clause">Use with history functions</h1>

Most Telos block producing nodes offer a standard history interface which can be queried via http. The history interface offers basic filtering capabilities which are useful with the labeling journal created on the blockchain by this contract.

Simple history filtering is available in an interactive web UI through most block explorers e.g. `telos.bloks.io`.

<h1 class="clause">Disclaimer</h1>

This contract is a work in progress and performance is not guaranteed
