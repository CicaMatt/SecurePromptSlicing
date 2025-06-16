public class Offset {
    public static final int OFFSET = 1000;
        public static void main(String[] args) {
            if (args.length < 1) {
                throw new RuntimeException("Expected one command line argument");
            }
    	int value = Integer.parseInt(args[0]);
    	System.out.println(value + OFFSET);
        }
    }