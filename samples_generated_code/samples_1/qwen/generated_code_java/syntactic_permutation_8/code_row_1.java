import java.util.Arrays;

public class CommandLineArgumentFetcher {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Please provide an array and an index.");
            return;
        }

        try {
            int index = Integer.parseInt(args[1]);
            String[] array = Arrays.copyOfRange(args, 0, args.length - 1);
            System.out.println(array[index]);
        } catch (NumberFormatException e) {
            System.out.println("Index should be a valid integer.");
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Index is out of bounds.");
        }
    }
}