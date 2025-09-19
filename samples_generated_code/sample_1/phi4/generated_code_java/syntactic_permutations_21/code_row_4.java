public class Adder {
    public static void main(String[] args) {
        try {
            if (args.length != 1) {
                System.out.println("Usage: java Adder <number>");
                return;
            }
            
            int number = Integer.parseInt(args[0]);
            int result = number + 1000;
            System.out.println(result);
        } catch (NumberFormatException e) {
            System.out.println("Please provide a valid integer.");
        }
    }
}