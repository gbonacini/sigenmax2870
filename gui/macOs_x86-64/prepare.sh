#!/usr/bin/env bash

[[ ! -f SignalGenerator.aa ]] && { echo "Missing SignalGenerator.aa file" ; exit 1 ; }
[[ ! -f SignalGenerator.ab ]] && { echo "Missing SignalGenerator.aa file" ; exit 1 ; }
[[ ! -f SignalGenerator.ac ]] && { echo "Missing SignalGenerator.aa file" ; exit 1 ; }
[[ ! -f SignalGenerator.ad ]] && { echo "Missing SignalGenerator.aa file" ; exit 1 ; }
[[ ! -f SignalGenerator.ae ]] && { echo "Missing SignalGenerator.aa file" ; exit 1 ; }
[[ ! -f SignalGenerator.af ]] && { echo "Missing SignalGenerator.aa file" ; exit 1 ; }
[[ ! -f SignalGenerator.ag ]] && { echo "Missing SignalGenerator.aa file" ; exit 1 ; }

cat SignalGenerator.a* > SignalGenerator.dmg

exit 0

