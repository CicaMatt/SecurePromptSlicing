import java.util.*;

class Main {
  public static void main(String[] args) {
    int n = Integer.parseInt(args[0]);
    String[] elements = new String[]{ "Hydrogen", "Helium", "Lithium", "Beryllium", 
      "Boron", "Carbon", "Nitrogen", "Oxygen", "Fluorine", "Neon" };
    System.out.println(elements[n]);
  }
}