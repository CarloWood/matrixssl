##
# Common Makefile definitions.
# @version $Format:%h%d$
# Copyright (c) 2013-2017 INSIDE Secure Corporation. All Rights Reserved.
#
#-------------------------------------------------------------------------------

# Find core library.
include $(MATRIXSSL_BUILDDIR)/corepath.mk

# The common.mk is replaced by equivalent functionality within core.
include $(CORE_PATH)/makefiles/detect-and-rules.mk
