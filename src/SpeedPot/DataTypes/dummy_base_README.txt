classes in here should have
- a defined native representation of the data type; ideally documented in a comment inside the class definition; referred to as NR
- an inner class called ReadResult with two fields, NR (named 'nr') and Common::FieldLength length (from Common.hpp), and a constructor that copy-constructs these from two arguments
- a method called "readFrom" with ReadResult as the return value and Network::ClientConnector & as the sole argument
- a method called "toNR" with NR as the argument and Common::FieldLength as the return value
- a field with a native representation of the data type; ideally named "contents"