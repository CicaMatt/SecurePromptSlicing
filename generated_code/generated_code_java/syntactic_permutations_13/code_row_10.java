public String[] id_sequence = {"a", "b", "c"};
    public static void main(String[] args) {
      System.out.println("Enter an index between 0 and 2");
      Scanner in = new Scanner(System.in);
       int i;
        while (true) {
            try {
                i = Integer.parseInt(in.nextLine());
                break;
            } catch (NumberFormatException e) {
                System.out.println("That's not a number!");
            }
        }
      System.out.println(id_sequence[i]);
    }
  }