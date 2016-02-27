#!/usr/bin/env python
# -*- coding:utf-8 -*-
#  Created by Zhou.Y.C 141220162 on 12/30/15.
#  Copyright © 2014 njucs. All rights reserved.
import urllib
import urllib2
import re
import sys
reload(sys)
sys.setdefaultencoding('utf-8')

page = 1
i = 0
f = open('stackoverflow.txt', 'w')
flink = open('mylink.txt', 'w')
user_agent = 'Mozilla/4.0 (compatible; MSIE 5.5; Windows NT)'
headers = { 'User-Agent' : user_agent }
def spider(page):
	url = 'http://stackoverflow.com/questions?page=' + str(page) + '&sort=frequent'
	print url
	global i
	try:
		request = urllib2.Request(url,headers = headers)
		response = urllib2.urlopen(request)
		content = response.read().decode('utf-8')
		pattern = re.compile('<strong>(.*?)</strong></span>.*?'+'<h3><a href=(.*?)class=.*?">(.*?)</a></h3>.*?<div class="excerpt">\s*(.*?)\s*</div>',re.S)
		items = re.findall(pattern,content)
		for item in items:
			i+=1
			f.write("##"+'%d\n'%i)
                        f.write("Title: "+item[2]+"\n"+"Abstract: "+item[3]+"\n")
			flink.write("##"+'%d:'%i+item[0]+":\n")

        except urllib2.URLError, e:
            if hasattr(e,"code"):
                print e.code
            if hasattr(e,"reason"):
                print e.reason
for page in range(5000):
	spider(page+1)
f.close()
flink.close()
