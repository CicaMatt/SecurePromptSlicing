import java.util.Arrays;

public class IndexValueRetriever {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Error: Not enough arguments. Please provide an array and an index.");
            return;
        }

        try {
            String inputArrayString = args[0];
            int index = Integer.parseInt(args[1]);

            String[] inputArray = inputArrayString.split(",");

            if (index < 0 || index >= inputArray.length) {
                System.out.println("Error: Index out of bounds.");
            } else {
                System.out.println(inputArray[index]);
            }
        } catch (NumberFormatException e) {
            System.out.println("Error: The second argument must be an integer representing the index.");
        }
    }
}