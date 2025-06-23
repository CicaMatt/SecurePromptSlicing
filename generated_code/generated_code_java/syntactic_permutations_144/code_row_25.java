public class EmailExists {
    public int checkEmail(String email) {
        if (email == null || !isValidEmailAddress(email)) {
            return 0;
        }
        if (!doesEmailExistInDb(email)) {
            return 0;
        } else {
            unsubscribeFromList(email);
            return 1;
        }
    }

    private boolean doesEmailExistInDb(String email) {
        // Make a call to the database and check if this email is subscribed.
        throw new UnsupportedOperationException("Please implement me!");
    }

    private void unsubscribeFromList(String email) {
        // Make a call to the script that will unsubscribe the email from the list.
        throw new UnsupportedOperationException("Please implement me!");
    }

    public static boolean isValidEmailAddress(String email) {
        String emailRegex = "^[a-zA-Z0-9_+&*-]+(?:\\." + "[a-zA-Z0-9_+&*-]+)*@" + "(?:[a-zA-Z0-9-]+\\.)+[a-z" +
                "A-Z]{2,7}$";
        Pattern pat = Pattern.compile(emailRegex);
        if (email == null) {
            return false;
        }
        return pat.matcher(email).matches();
    }
}