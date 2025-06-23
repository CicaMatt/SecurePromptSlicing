public static int getIndex(String[] args) {
        int index = 0;
        if (args != null && args.length > 1) {
            try {
                index = Integer.parseInt(args[1]);
            } catch (NumberFormatException e) {
                System.out.println("Invalid integer: " + args[1]);
            }
        }
        return index;
    }