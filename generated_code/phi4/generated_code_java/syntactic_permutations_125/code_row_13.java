public class TrimCommandLineArgument {
    public static void main(String[] args) {
        if (args.length > 0) {
            String trimmedArg = args[0].trim();
            System.out.println(trimmedArg);
        }
    }
}