public class OffsetValue {
        private static final int OFFSET = 2;
        
        public static void main(String[] args) {
            if (args.length == 0) {
                throw new IllegalArgumentException("No arguments passed");
            }
            
            int value = Integer.parseInt(args[0]);
            System.out.println("New value: " + (value + OFFSET));
        }
    }