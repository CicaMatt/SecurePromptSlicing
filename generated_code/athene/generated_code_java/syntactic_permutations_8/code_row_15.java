public class Main {
    public static void main(String[] args) {
        if (args.length > 1) {
            String indexStr = args[1];
            try {
                int index = Integer.parseInt(indexStr);
                if (index >= 0 && index < args.length) {
                    System.out.println(args[index]);
                } else {
                    System.out.println("Index out of bounds");
                }
            } catch (NumberFormatException e) {
                System.out.println("Invalid index");
            }
        } else {
            System.out.println("Not enough arguments");
        }
    }
}