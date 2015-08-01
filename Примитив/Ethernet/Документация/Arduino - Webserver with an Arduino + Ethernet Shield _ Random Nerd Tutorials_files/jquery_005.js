/*
* Placeholder plugin for jQuery
* ---
* Copyright 2010, Daniel Stocks (http://webcloud.se)
* Released under the MIT, BSD, and GPL Licenses.
*/
;(function(a){function b(b){this.input=b;if(b.attr("type")=="password"){this.handlePassword()}a(b[0].form).submit(function(){if(b.hasClass("placeholder")&&b[0].value==b.attr("placeholder")){b[0].value=""}})}b.prototype={show:function(a){if(this.input[0].value===""||a&&this.valueIsPlaceholder()){if(this.isPassword){try{this.input[0].setAttribute("type","text")}catch(b){this.input.before(this.fakePassword.show()).hide()}}this.input.addClass("placeholder");this.input[0].value=this.input.attr("placeholder")}},hide:function(){if(this.valueIsPlaceholder()&&this.input.hasClass("placeholder")){this.input.removeClass("placeholder");this.input[0].value="";if(this.isPassword){try{this.input[0].setAttribute("type","password")}catch(a){}this.input.show();this.input[0].focus()}}},valueIsPlaceholder:function(){return this.input[0].value==this.input.attr("placeholder")},handlePassword:function(){var b=this.input;b.attr("realType","password");this.isPassword=true;if(a.browser.msie&&b[0].outerHTML){var c=a(b[0].outerHTML.replace(/type=(['"])?password\1/gi,"type=$1text$1"));this.fakePassword=c.val(b.attr("placeholder")).addClass("placeholder").focus(function(){b.trigger("focus");a(this).hide()});a(b[0].form).submit(function(){c.remove();b.show()})}}};var c=!!("placeholder"in document.createElement("input"));a.fn.placeholder=function(){return c?this:this.each(function(){var c=a(this);var d=new b(c);d.show(true);c.focus(function(){d.hide()});c.blur(function(){d.show(false)});if(a.browser.msie){a(window).load(function(){if(c.val()){c.removeClass("placeholder")}d.show(true)});c.focus(function(){if(this.value==""){var a=this.createTextRange();a.collapse(true);a.moveStart("character",0);a.select()}})}})};a(document).ready(function(){a("input[placeholder], textarea[placeholder]").placeholder()})})(opjq)