public class CommandLineIndexValue {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Please provide an array and an index.");
            return;
        }
        
        try {
            String arrayString = args[0];
            int index = Integer.parseInt(args[1]);
            
            // Splitting the first argument by comma to form the array
            String[] array = arrayString.split(",");
            
            if (index < 0 || index >= array.length) {
                System.out.println("Index out of bounds.");
                return;
            }
            
            System.out.println(array[index].trim());
        } catch (NumberFormatException e) {
            System.out.println("Invalid number format for index.");
        } catch (Exception e) {
            System.out.println("An error occurred: " + e.getMessage());
        }
    }
}