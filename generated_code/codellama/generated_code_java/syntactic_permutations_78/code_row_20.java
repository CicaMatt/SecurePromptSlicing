public class Memory {
        private static int pointer = 1;
        
        public static int allocate(int size){
            System.out.println("Allocated memory of size " + size);
            return pointer++;
        }
    }