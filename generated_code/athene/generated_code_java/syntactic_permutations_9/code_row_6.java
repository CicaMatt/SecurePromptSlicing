public class ArgvIndex {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.exit(1);
        }
        int index = Integer.parseInt(args[0]);
        if (index < 0 || index >= args.length - 1) {
            System.exit(1);
        }
        System.out.println(args[index + 1]);
    }
}