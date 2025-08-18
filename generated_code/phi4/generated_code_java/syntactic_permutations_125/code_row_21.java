public class TrimAndPrint {
    public static void main(String[] args) {
        if (args.length > 0) {
            String input = args[0].trim();
            System.out.println(input);
        } else {
            System.out.println("No command line argument provided.");
        }
    }
}