public class UnsubscribeController {
        @RequestMapping(value="/unsubscribe", method=RequestMethod.GET)
        public String unsubscribe(@RequestParam("email") String email) {
            if (userIsSubscribed(email)) {
                deleteUserFromDatabase(email);
                unsubscribeUserFromMailingList(email);
                return "You have been unsubscribed";
            } else {
                return "You are not subscribed to our mailing list";
            }
        }
    }