public static String getArgument(String[] argv) {
      int index = Integer.parseInt(argv[0]);
      if (index >= 0 && index < argv.length - 1) {
        return argv[index];
      } else {
        throw new IllegalArgumentException("Index out of bounds");
      }
    }