#!/bin/bash
# Protection management: chmod, chown, chgrp
# chown/chgrp may require suitable privileges on your Linux system.
touch report.txt
ls -l report.txt
chmod 755 report.txt
ls -l report.txt
chmod u-x,go-rx report.txt
ls -l report.txt
# Uncomment the next commands only when you have permission:
# sudo chown nobody report.txt
# sudo chgrp nogroup report.txt
