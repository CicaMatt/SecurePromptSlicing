import java.util.*;

public class ElementFinder {
    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Missing argument");
            return;
        }
        
        int index = Integer.parseInt(args[0]);
        String[] elements = {"Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune"};
        
        if (index < 0 || index >= elements.length) {
            System.out.println("Invalid index");
            return;
        }
        
        String element = elements[index];
        System.out.println(element);
    }
}