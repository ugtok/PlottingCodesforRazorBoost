#!/usr/bin/env python

import os,sys
from ROOT import *
from string import *
import argparse

date = sys.argv[1]

fresh = True

# S i g n a l  R e g i o n s  L i s t
SRs = ['SR_Had_1htop',
	  'SR_Had_2htop',
	  'SR_Had_V_b_45j',
	  'SR_Had_V_b_6j',
	  'SR_Had_1V_0b_34j',
	  'SR_Had_1V_0b_5j',
	  'SR_Had_2V_0b_24j',
	  'SR_Had_2V_0b_5j',
	  'SR_Had_H_b_45j',
	  'SR_Had_H_b_6j',
	  'SR_Had_HV_b_6j',
	  'SR_Had_H_0b_34j',
	  'SR_Had_H_0b_5j',
	  'SR_Had_HV_0b_24j',
	  'SR_Had_HV_0b_5j',
	# Isolated lepton signal regions
	  'SR_Lep_1htop',
	  'SR_Lep_V_b',
	  'SR_Lep_V_0b',
	  'SR_Lep_H_b',
	  'SR_Lep_H_0b',
	# Non-isolated lepton signal regions
	  'SR_Leptop_0htop',
	  'SR_Leptop_1htop',
	  'SR_Lepjet_0V_24j',
	  'SR_Lepjet_0V_5j',
	  'SR_Lepjet_1V_24j',
	  'SR_Lepjet_1V_5j',
]


# P r o c c e s e s
'''
procs = [
	'Signal',
	'Background'
	]
'''

# S y s t e m a t i c s
systematics = [
	"",
	"_topptUp",
	"_topptDown",
	"_isrUp",
	"_isrDown",
	"_pileupUp",
	"_pileupDown",
	"_L1PreFiringUp",
	"_L1PreFiringDown",
	"_alphasUp",
	"_alphasDown",
	"_scaleUp",
	"_scaleDown",
	#"_lostlepUp", #will comment out
	#"_lostlepDown", #will comment out
	"_triggerUp",
	"_triggerDown",
	"_jesUp",
	"_jesDown",
	"_jerUp",
	"_jerDown",
	"_metUp",
	"_metDown",
	"_RescaleAK8Up",
	"_RescaleAK8Down",
	"_BoostTagUp",
	"_BoostTagDown",
	"_BoostTag_FastsimUp",
	"_BoostTag_FastsimDown",
	"_BoostmisTagUp",
	"_BoostmisTagDown",
	"_BoostmisTag_FastsimUp", #Close after Changgi updated
	"_BoostmisTag_FastsimDown", #Close ...
	"_EleRecoUp",
	"_EleRecoDown",
	"_EleIDUp",
	"_EleIDDown",
	"_EleIsoUp",
	"_EleIsoDown",
	"_EleFastsimUp",
	"_EleFastsimDown",
	"_PhoIDUp",
	"_PhoIDDown",
	"_MuonTrackUp",
	"_MuonTrackDown",
	"_MuonFullsimUp",
	"_MuonFullsimDown",
	"_MuonFastsimUp",
	"_MuonFastsimDown",
	"_BTagUp",
	"_BTagDown",
	"_BTagFastsimUp",
	"_BTagFastsimDown",
	"_cf_QTWUp",
	"_cf_QTWDown",
	"_cf_NonIso_Up",
	"_cf_NonIso_Down",
	"_cf_ZUp",
	"_cf_ZDown",
]

maindir = '/afs/cern.ch/user/u/utok/private/razorlimits/'
output = maindir+'Background/'+date

if not os.path.exists(output):
	os.system('mkdir -p '+output)

# Get Total BG files

file_background = TFile(maindir+'Background/Background.root')

h_bgssr = []
# Get BG histogram lists for each SR:
for sr in SRs:       
  h = file_background.Get("Background/MRR2_S_bkg_"+sr+"_new")        
  h.SetName("MRR2_"+sr+"_new")
  h_bgssr.append(h)

# Write the systematics beginning lines
sheet = '''
------------------------------------------------------------
Total Background         systematics _vs_ SRs           
------------------------------------------------------------
'''

document = output+'/Background_syst.txt'
if fresh: 
	doc = open(document, 'w')

# Write the datacard header
doc.write(sheet)

# Write processes and rates
row = '%-30s ' % 'syst/SRs'

SR_number = 0
for s in range(len(SRs)):
	row = row+'%-16s' % SRs[s][3:]

doc.write(row+'\n')

doc.write('-----------------------------------------\n')

# Loop over systematics
for sy in range(1,len(systematics),2):	# Loop over syst
	row = '%-30s ' % systematics[sy][:-2]

	for s in range(len(SRs)):	# LOOP OVER SRs
		dash = '-'
		up_perc = 0
		down_perc = 0
		bin_count = 0
		for ibin in range(1, h_bgssr[s].GetXaxis().GetNbins()+1): 
			bin_count += 1
			if h_bgssr[s].GetBinContent(ibin, 1) > 0:
				up = fabs(round(h_bgssr[s].GetBinContent(ibin, sy+1) / h_bgssr[s].GetBinContent(ibin, 1), 3))
				down = fabs(round(h_bgssr[s].GetBinContent(ibin, sy+2) / h_bgssr[s].GetBinContent(ibin, 1), 3))
				if up == 0.000: up = 0.001
				if down == 0.000: down = 0.001

				if up != 0.001: 
					up_perc += fabs(round((up - 1) *100, 2))
				else:
					up_perc = 999 

				if down != 0.001: 
					down_perc += fabs(round((up - 1) *100, 2))
				else: 
					down_perc = 999

		if up_perc != 999 or down_perc != 999:
			dash = str(round(down_perc/bin_count,1))+'%/-'+str(round(up_perc/bin_count,1))+'-%'

		row = row +'%-16s' % dash

	doc.write(row+'\n')










