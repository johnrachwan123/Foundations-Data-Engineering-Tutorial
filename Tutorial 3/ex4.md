#### 4
`uint64_t pattern = 0x0A0A0A0A0A0A0A0A;`  hex value of `\n` is `0A`

`uint64_t all0iffNl = block ^ pattern;` `0^0 = 1^1 = 0`, `1^0 = 0^1 = 1`

#### 5
for 8 bit `searchResult` we have at most 0111 1111 and at least 0000 0001 so adding `0x7F=0111111` will make the 
highest bit of `searchResult` 1 if and only if `searchResult != 0`

`uint64_t low = 0x7F7F7F7F7F7F7F7F;`

`uint64_t highestBitSetIffByteNot0 = searchResult + low;` 

#### 6
If `highestBitSetIffByteNot0 = 0XXX XXXX` then `highestSetIf0 = 1000 0000` else if `highestBitSetIffByteNot0 = 1XXX XXXX`
`highestSetIf0 = 0000 0000`

`uint64_t high = 0 x8080808080808080;`

`uint64_t highestSetIf0 = ~highestBitSetIffByteNot0 & high` 

We get each byte of `high` to be equal `1000 0000` and we negate the `highestBitSetIffByteNot0` so we for sure zero out
all the bits except from the first. By `&` operation and we keep the first set only if the `highestBitSetIffByteNot0 = 0XXX XXXX`

#### 7

`ipattern = 0 x0A0A0A0A0A0A0A0A;` \\ hex value of ’\n ’ is `0A`

`uint64_t low = 0 x7F7F7F7F7F7F7F7F;`

`uint64_t high = 0 x8080808080808080;`

`all0iffNl = block ^ pattern;` \\ make all new line chars zero and the rest non zero

`highestBitSetIffByteNot0 = all0iffNl + low;` \\ make the highest bit set if and only if the `block` was not the new line char

`highestSetIf0 = ~ highestBitSetIffByteNot0 & high;` \\ now we have the highest bit set only for the new line

#### 8

`pattern = 0x0A0A0A0A0A0A0A0A;`

`uint64_t low = 0x7F7F7F7F7F7F7F7F;`

`uint64_t high = 0x8080808080808080;`


`uint64_t lowChar = ~ block & high` // add lowChar to know which one of the chars was <= 127  (For `block = 1XXX XXX` we have `0000 0000` otherwise `1000 0000`)

`all0iffNl = block ^ pattern & low;` // added & low to install invariant : byte values <= 127, by doing `& low` we make sure that the highest bit is `0` so we can proceed as before

`highestBitSetIffByteNot0 = all0iffNl + low;`

`highestSetIf0 = ~ highestBitSetIffByteNot0 & high;`

`result = highestSetIf0 & lowChar;` // now we "delete" all the false positives (i.e. we discard `1000 1010` because we are only interested in `0000 1010`)

#### 9 BONUS

How would you solve this if you want to match a pattern that is larger than 128?

