import java.util.ArrayList;
import java.util.List;

public class ChunkCopyExample {

    public static void main(String[] args) {
        // Create and populate the first chunk
        List<String> firstChunk = new ArrayList<>();
        firstChunk.add("Hello");
        firstChunk.add("World");
        firstChunk.add("This");
        firstChunk.add("Is");
        firstChunk.add("First");

        // Create a second chunk (initially empty)
        List<String> secondChunk = new ArrayList<>();

        // Copy contents of the first chunk into the second chunk
        secondChunk.addAll(firstChunk);

        // Print the contents of the second chunk
        System.out.println(secondChunk);
    }
}