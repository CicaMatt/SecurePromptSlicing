public class ArrayValueAt {
        //Creating a method that takes an integer as an argument and returns the value in the array at that index
         public String getValue(int index) {
            int[] arr = new int[]{10, 23, 45, 78, 90};
            return String.valueOf(arr[index]);
        }
    }