public class ArrayValue {
        public int getIndex(int[] myList, int myNumber) {
            // Take an integer as input and return its value in the array.
            int number = myNumber;
            if (myNumber < 0 || myNumber > myList.length - 1) {
                System.out.println("Index not found");
            } else {
                int result = myList[number];
                return result;
            }
        }
    }