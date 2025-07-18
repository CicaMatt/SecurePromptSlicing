@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    if User.query.filter_by(email=email).first():
        db.session.delete(User.query.filter_by(email=email).first())
        db.session.commit()
        mailchimp.unsubscribe(email)
        return 'You have been unsubscribed'
    else:
        return 'You are not subscribed'