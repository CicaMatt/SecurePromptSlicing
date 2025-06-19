public class IndexOf {
        private static int[] testArray = {1, 2, 3, 4, 5};
        
        public static void main(String args[]){
            System.out.println("Index of 5 is " + getIndex(5));
        }
    
        private static int getIndex(int input){
            for (int i = 0; i < testArray.length; i++) {
                if (testArray[i] == input) {
                    return i;
                }
            }
            return -1;
        }
    }