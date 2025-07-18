import java.util.*;

class Main {
  public static void main(String[] args) {
    ArrayList<Integer> chunk1 = new ArrayList<>();
    ArrayList<Integer> chunk2 = new ArrayList<>();

    for (int i = 0; i < 5; i++) {
      chunk1.add(i);
    }

    for (int i : chunk1) {
      chunk2.add(i);
    }

    System.out.println(chunk2);
  }
}