quackmessage_sources = [
  'main.c',
  'quackmessage-application.c',
  'quackmessage-window.c',
]

quackmessage_deps = [
  dependency('gtk4'),
  dependency('libadwaita-1', version: '>= 1.4'),
]

quackmessage_sources += gnome.compile_resources('quackmessage-resources',
  'quackmessage.gresource.xml',
  c_name: 'quackmessage'
)

executable('quackmessage', quackmessage_sources,
  dependencies: quackmessage_deps,
       install: true,
)
