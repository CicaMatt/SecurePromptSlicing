public class TrimAndPrint {
    public static void main(String[] args) {
        if (args.length > 0) {
            String trimmedArgument = args[0].trim();
            System.out.println(trimmedArgument);
        } else {
            System.out.println("No argument provided.");
        }
    }
}