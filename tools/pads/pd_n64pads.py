"""Rewrite a Perfect Dark port pd.ini for N64-style USB pads (clones that report as a
Switch Pro). Measured with tools/padtest: A=a B=b Z=lefttrigger L/R=shoulders
start=start, C buttons on the right stick, d-pad, main stick = left stick.

Per player: SwapSticks=0 (N64 stick = physical left stick), StickCButtons=1 (right stick
-> digital C buttons), and pad binds that map each N64 button to itself. Keyboard and
mouse binds are kept. Usage: python3 -I pd_n64pads.py <pd.ini>"""
import re, sys

JOY = {  # PD bind -> pad inputs (JOYn_ prefix added per player)
    'A_BUTTON': ['A'], 'B_BUTTON': ['B'], 'Z_TRIG': ['LTRIGGER'],
    'R_TRIG': ['RSHOULDER'], 'L_TRIG': ['LSHOULDER'], 'START_BUTTON': ['START'],
    'U_JPAD': ['DPAD_UP'], 'D_JPAD': ['DPAD_DOWN'], 'L_JPAD': ['DPAD_LEFT'], 'R_JPAD': ['DPAD_RIGHT'],
    'ACCEPT_BUTTON': ['A'], 'CANCEL_BUTTON': ['B'],
}

def main(path):
    lines = open(path).read().split('\n')
    out, sec = [], None
    for line in lines:
        m = re.match(r'^\[(.+)\]$', line.strip())
        if m:
            sec = m.group(1)
            out.append(line)
            continue
        pm = re.match(r'^Input\.Player([1-4])(\.Binds)?$', sec or '')
        if pm and '=' in line:
            n, binds = pm.group(1), pm.group(2)
            key, val = line.split('=', 1)
            if not binds:
                if key == 'SwapSticks': line = 'SwapSticks=0'
                elif key == 'StickCButtons': line = 'StickCButtons=1'
            else:
                keep = [v.strip() for v in val.split(',') if v.strip() and not v.strip().startswith('JOY') and v.strip() != 'NONE']
                keep += ['JOY%s_%s' % (n, j) for j in JOY.get(key, [])]
                line = '%s=%s' % (key, ', '.join(keep) if keep else 'NONE')
        out.append(line)
    open(path, 'w').write('\n'.join(out))

if __name__ == '__main__':
    main(sys.argv[1])
