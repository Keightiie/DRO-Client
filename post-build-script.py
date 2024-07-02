import os
import sys
import glob
import shutil

if len(sys.argv) != 2:
    print('This script takes exactly one argument: win32, win64 or macx64')
    exit(1)

libs_dir = sys.argv[1]
pro_dir = os.path.dirname(os.path.realpath(__file__))
build_dir = os.getcwd()

# Assume this script is only run for release builds since there's no way to check
is_release = True
if not is_release:
    print('Not a Release build, do not copy libraries')
    exit(1)

# Check what platform the build directory is
if glob.glob(build_dir + '/release/*.exe'):
    platform = 'win'
    print('Windows build detected. Proceeding to copy Windows libraries')
elif glob.glob(build_dir + '/*.app'):
    platform = 'mac'
    macapp_dir = glob.glob(build_dir + '/*.app')[0]
    print('MacOS build detected. Proceeding to copy MacOS libraries')
else:
    platform = 'unknown'
    print('Unable to detect platform of build binary.')
    exit(1)

# Copies all the DLLs over
if platform == 'win':
    for file in glob.glob(pro_dir + '/3rd/' + libs_dir + '/*.dll'):
        print('Copying', file)
        shutil.copy2(file, build_dir + '/release/')
    for file in glob.glob(pro_dir + '/3rd/' + libs_dir + '/*.lib'):
        print('Copying', file)
        shutil.copy2(file, build_dir + '/release/')
    print('Copying directory ' + pro_dir + '/3rd/' + libs_dir + '/plugins')
    shutil.copytree(pro_dir + '/3rd/' + libs_dir + '/plugins', build_dir + '/release/plugins', dirs_exist_ok=True, symlinks=True, ignore_dangling_symlinks=True)
elif platform == 'mac':
    if not os.path.isdir(macapp_dir + '/Contents/Frameworks/'):
        os.makedirs(macapp_dir + '/Contents/Frameworks/')
    for file in glob.glob(pro_dir + '/3rd/' + libs_dir + '/*.dylib'):
        print('Copying', file)
        shutil.copy2(file, macapp_dir + '/Contents/Frameworks/')
    for file in glob.glob(pro_dir + '/3rd/' + libs_dir + '/*.framework'):
        print('Copying', file)
        dest_dir = macapp_dir + '/Contents/Frameworks/' + os.path.basename(file)
        if os.path.isdir(dest_dir):
            shutil.rmtree(dest_dir)
        shutil.copytree(file, dest_dir, dirs_exist_ok=True, symlinks=True, ignore_dangling_symlinks=True)
