(function($){

Ibles.package("Ibles.views");

Ibles.views.EmailVerificationHeader =  Backbone.View.extend({
    className:'sticky-email-verification',
    events:{
        'click .send-verification':'showVerificationModal'
    },
    initialize:function(){
        this.render();
    },
    showVerificationModal:function(e){
        e.preventDefault();
        $('.verification-modal').modal('show');
    },
    render:function(){
        var that = this;
        return Ibles.fetchTemplate("/static/templates/verify_email_templates.html").done(function(JST){
            that.$el.html(JST['#verify-header-template'](Ibles.session.toJSON()));
            that.$el.insertBefore('#gbl-header');
        });
        return this;
    }
})

Ibles.views.EmailVerificationModal = Backbone.View.extend({
    className:'modal fade verification-modal',
    events:{
        'click .send-email':'verify'
    },
    initialize: function() {
        this.render();
    },
    render:function(){
        var that = this;
        return Ibles.fetchTemplate("/static/templates/verify_email_templates.html").done(function(JST){
            that.$el.html(JST['#verify-email-modal-template'](Ibles.session.toJSON()));
            that.$el.insertBefore('#gbl-header');
        });
        return this;
    },
    verify:function(e){
        e.preventDefault();
        var promise,
            that = this,
            email = this.$('.email-input').val();
        this.$('.send-email').button('loading');

        if (this.validateEmail(email)){
            this.$('.send-email').button('sending');
            if (email === Ibles.session.get('email')){
                promise = this.sendVerificationEmail();
            } else {
                promise = this.saveProfile();
            }
            promise.then(function(data){
                $.cookie('verifyHeader','false',{path: '/' });
                $('.sticky-email-verification').hide();
                that.$('.send-email').button('finished');
                setTimeout(function(){that.$el.modal('hide');},1000);
            }).fail(function(jqXHR){
                that.$('.send-email').button('reset');
                if (!_.isUndefined(jqXHR.responseJSON) && !_.isUndefined(jqXHR.responseJSON.error)){
                    that.$('.send-error').text(jqXHR.responseJSON.error);
                }
                that.$('.send-error').css('display','inline-block');
            })
        } else{
            this.$('.send-email').button('reset');
        }

    },
    saveProfile: function(){
        return Ibles.API.postRequest('saveProfile',{
            email:this.$('.email-input').val()
        })
    },
    sendVerificationEmail: function(){
        return Ibles.API.getRequest('emailVerificationSend')
    },
    validateEmail: function(email){
        var input = this.$('.email-input');
        if (input.is(':invalid')){
            input.tooltip("destroy")
                .data("title", "Invalid email address!")
                .addClass("error")
                .tooltip();
            input.focus();
            return false;
        }
        else{
            input.removeClass("error").tooltip("destroy");
            return true;
        }
    }
});
})(jQuery)
