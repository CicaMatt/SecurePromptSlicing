public class IndexOf {
        public static int getIndex(int[] arr, int element) {
            for (int i = 0; i < arr.length; i++) {
                if (arr[i] == element) {
                    return i;
                }
            }
            return -1;
        }
    
        public static void main(String[] args) {
            int[] arr = new int[]{5, 8, 9, 4, 3, 2};
            System.out.println("Index of 4 is: " + getIndex(arr, 4));
        }
    }