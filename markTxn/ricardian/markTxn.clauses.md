<h1 class="clause">Purpose</h1>

This contract supports a lightweight system for annotating payments made on chain. This is intended to support analysis of how the economic system is working.

The contract itself implements no semantics, although default semantics are described in the ricardian contract. There is no validation or protection against erroneous annotations, whether by mistake or malice. Persons writing analysis tools would be advised to implement outlier checking and filtering (e.g. based on a whitelist of annotators).
1. mark - assigns a category (e.g. "product sale") to a transaction
2. addcategory - adds a new category name to the list of acceptable categories
3. delcategory - removes a category name
4. categories - returns the list of categories

<h1 class="clause">Issuing Actions</h1>

Example
```
cleos -u https://api.telos.caleos.io push transaction '{
...
```

<h1 class="clause">Effect</h1>

This contract leaves only a "journal" of labeling events on the blockchain. The contract contains no database which can be queried about annotations. (The only table maintained by the contract is a list of known category names.)

<h1 class="clause">Usage</h1>

It is valid for there to be multiple **mark** actions recorded on the blockchain referencing the same transaction. There are several reasons for this to occur, and analysis software should be designed to handle these situations. In particular
1. Two different annotators (e.g. the buyer and seller) may both submit **mark** actions independently. It is not certain that they will choose the same category to describe the transaction.
2. Several categories may apply to the same transaction, e.g. a bundle of tree seedlings might be marked as "product sale", "agricultural", and "regenerative". Three **mark** actions would be recorded on the chain.
3. The mark function includes a parameter "fraction", with valid values ranging from 0 to 100 (percent). In basic usage, the fraction would be 100. However if a single payment transaction covered two different products or services with very different characteristics, a set of **mark** actions may be posted representing the different fractional components of the payment.

It may be useful for persons to perform "third party" category assignments, sometimes without direct knowledge of the transaction. These assignments may be estimates with limited accuracy. The **mark** action includes a "confidence" parameter which may take a value up to 100 (percent), which represents complete certainty. It is possible that automated software ("bots") will perform some category estimation.

Analysis software will sometimes see incomplete, contradictory, or simply mistaken data. When analysis software retrieves a **mark** event from the blockchain history, it will be able to see the identity of the account which submitted the action. The analysis software may choose to apply its own confidence weightings based on the submitter identity.

<h1 class="clause">Use with history functions</h1>

Most Telos block producing nodes offer a standard history interface which can be queried via http. The history interface offers basic filtering capabilities which are useful with the labeling journal created on the blockchain by this contract.

Simple history filtering is available in an interactive web UI through most block explorers e.g. `telos.bloks.io`.

<h1 class="clause">Disclaimer</h1>

This contract is a work in progress and performance is not guaranteed
