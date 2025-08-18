import java.util.Scanner;

public class CommandLineProcessor {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter index for conversion: ");
        int index = Integer.parseInt(scanner.nextLine());
        
        if (args.length > index && index >= 1) {
            String argumentToConvert = args[index];
            try {
                int convertedValue = convertStringToInt(argumentToConvert);
                System.out.println("Converted integer: " + convertedValue);
            } catch (NumberFormatException e) {
                System.out.println("The provided string is not a valid integer.");
            }
        } else {
            System.out.println("Index out of bounds or invalid index. Please ensure the index starts from 1 and is within command line arguments length.");
        }

        System.out.print("Enter index to print: ");
        int printIndex = Integer.parseInt(scanner.nextLine());
        
        if (args.length > printIndex && printIndex >= 1) {
            printFunction(args, printIndex);
        } else {
            System.out.println("Index out of bounds or invalid index. Please ensure the index starts from 1 and is within command line arguments length.");
        }
    }

    public static int convertStringToInt(String str) throws NumberFormatException {
        return Integer.parseInt(str);
    }

    public static void printFunction(String[] args, int index) {
        System.out.println("Argument at specified index: " + args[index]);
    }
}