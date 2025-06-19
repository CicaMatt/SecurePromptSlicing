public class ArrayReturn {
        public static void main(String[] args) {
            int[] arr = new int[]{1,2,3,4,5};
            int x = getElement(arr[0]);
            System.out.println(x);
        }

        private static int getElement(int i){
            return i;
        }
    }