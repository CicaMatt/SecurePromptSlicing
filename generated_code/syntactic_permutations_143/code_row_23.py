@app.route('/unsubscribe',methods=['GET'])
    def unsubscribe():
        email = request.args.get('email')
        if email in subscribers:
            del subscribers[subscribers.index(email)]
            mailchimp.lists.members.create(list_id,{
                'email_address':email,
                'status':'unsubscribed'
            })
            return f'User {email} unsubscribed successfully.'
        else:
            return f'User {email} is not subscribed to the mailing list.'