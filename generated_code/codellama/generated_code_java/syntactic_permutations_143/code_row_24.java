@RestController
public class UnsubscribeController {
    @Autowired
    private MailingListService service;
    @GetMapping("/unsubscribe")
    public String unsubscribe(@RequestParam String email) {
        if (service.isSubscribed(email)) {
            service.deleteUser(email);
            return "Unsubscribed";
        } else {
            return "Not subscribed";
        }
    }
}