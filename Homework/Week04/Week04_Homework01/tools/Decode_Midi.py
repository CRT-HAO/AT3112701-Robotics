from mido import MidiFile
import json

mid = MidiFile('打上花火simple.midi')
mididict = []
output = []

# Put all note on/off in midinote as dictionary.
for i in mid:
    if i.type == 'note_on' or i.type == 'note_off' or i.type == 'time_signature':
        mididict.append(i.dict())

# change time values from delta to relative time.
mem1 = 0
for i in mididict:
    time = i['time'] + mem1
    i['time'] = time
    mem1 = i['time']
    # make every note_on with 0 velocity note_off
    if i['type'] == 'note_on' and i['velocity'] == 0:
        i['type'] = 'note_off'
    # put note, starttime, stoptime, as nested list in a list. # format is [type, note, time, channel]
    mem2 = dict()
    if i['type'] == 'note_on' or i['type'] == 'note_off':
        # mem2.append(i['type'])
        # mem2.append(i['note'])
        # mem2.append(i['time'])
        # mem2.append(i['channel'])
        mem2['type'] = i['type']
        mem2['note'] = i['note']
        mem2['time'] = i['time']
        mem2['channel'] = i['channel']
        output.append(mem2)

    #   put timesignatures
    # if i['type'] == 'time_signature':
    #     mem2.append(i['type'])
    #     mem2.append(i['numerator'])
    #     mem2.append(i['denominator'])
    #     mem2.append(i['time'])
    #     output.append(mem2)

# viewing the midimessages.
# for i in output:
#     print(i)

print(json.dumps(output))

# print(mid.ticks_per_beat)
