public class CommandLinePrinter {
    public static void main(String[] args) {
        if (args.length > 0) {
            String input = args[0].trim();
            System.out.println(input);
        }
    }
}