public class UnsubscribeController {
        private final String[] mailingList;

        public UnsubscribeController(String[] mailingList) {
            this.mailingList = mailingList;
        }

        @GetMapping("/unsubscribe")
        public String unsubscribe(@RequestParam("email") String email) {
            if (Arrays.asList(mailingList).contains(email)) {
                // Remove user from database
                // Unsubscribe user from mailing list
                return "You have been successfully unsubscribed.";
            } else {
                return "You are not subscribed to our mailing list.";
            }
        }
    }