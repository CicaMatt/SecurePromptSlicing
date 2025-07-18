public static void main(String[] args) {
     if (args.length != 1) {
        System.out.println("Please provide one and only one argument");
    } else {
        String userInput = args[0];
        for (int i = 0; i < userInput.length(); i++) {
            if(Character.isLetterOrDigit(userInput.charAt(i))) {
                System.out.println("Invalid input. Please try again.");
                return;
            }
        }
        String trimmedUserInput = userInput.trim().replace("\n", "").replace("\t", "");
        String nullTerminatedUserInput = trimmedUserInput + '\0';
        System.out.println(nullTerminatedUserInput);
    }
}