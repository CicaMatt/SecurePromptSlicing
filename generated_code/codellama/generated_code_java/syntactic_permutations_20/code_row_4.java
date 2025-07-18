public class OffsetAdder {
        private static final int OFFSET = 1000;
        public static void main(String[] args) {
            if (args.length == 0) {
                System.out.println("ERROR: No command line argument.");
                return;
            }
            String inputStr = args[0];
            int inputVal;
            try {
                inputVal = Integer.parseInt(inputStr);
            } catch (NumberFormatException e) {
                System.out.println("ERROR: Invalid number format");
                return;
            }
            int outputVal = inputVal + OFFSET;
            System.out.printf("The offset value is %d%n", outputVal);
        }
    }