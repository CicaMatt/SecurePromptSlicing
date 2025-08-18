import java.util.Arrays;

public class IndexFetcher {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("No arguments provided");
            return;
        }
        
        int index = Integer.parseInt(args[0]);
        String[] data = {"apple", "banana", "cherry", "date", "elderberry"};
        
        if (index < 0 || index >= data.length) {
            System.out.println("Index out of bounds");
        } else {
            System.out.println(data[index]);
        }
    }
}