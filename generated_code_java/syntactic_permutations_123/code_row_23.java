public class HelloWorld {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("You must provide exactly one argument.");
            return;
        } else if (!(args[0] instanceof String)) {
            System.out.println("Your argument was not a string.");
            return;
        } else {
            String name = args[0].trim();
            System.out.print("Hello ");
            for (int i = 0; i < name.length(); i++) {
                if (name.charAt(i) == '\n') {
                    continue;
                } else {
                    System.out.println(name.charAt(i));
                }
            }
            return;
        }
    }
}