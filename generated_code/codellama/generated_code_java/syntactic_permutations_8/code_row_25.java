public static String getValueFromArgs(String[] args) {
        if (args == null || args.length < 2) {
            throw new IllegalArgumentException("Not enough arguments");
        }
        return args[1];
    }